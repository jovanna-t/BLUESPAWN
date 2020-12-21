#pragma once

#include <string>
#include <optional>

enum class EnforcementLevel {
	None = 0,
	Low = 1,
	Moderate = 2,
	High = 3,
	All = 4,
};

/**
 * \brief A policy to be enforced by a mitigation. Each mitigation policy represents a single setting,
 *        configuration, or change to be enforced. 
 * 
 * \note When possible, mitigation policies should be extended for types of mitigation policies rather
 *       than for individual mitigations. Mitigation policies involving registry keys, for example, can
 *       be implemented by instantiating a RegistryPolicy and specifying the keys and values in question.
 */
class MitigationPolicy {

	/// A boolean tracking whether the policy should be enforced
	bool isEnforced;

	/// The name of the policy. This should attempt to very briefly describe what it does (i.e. "Disable Anonymously
	/// Accessible Named Pipes")
	std::wstring name;

	/// An optional explanation for the policy (i.e. "Anonymously accessible named pipes can be used in X, Y and Z attacks
	/// and should be disabled. See abc.com/xyz for more info [v-123]")
	std::optional<std::wstring> description;

	/// The level at which this mitigaiton policy should begin to be enforced. This should be Low, Moderate, or High
	EnforcementLevel level;

public:

	/**
	 * \brief Instantiates a MitigationPolicy object. This should only be called from withing derived classes' 
	 *        constructors.
	 * 
	 * \param name The name of the mitigation policy. This should attempt to very briefly describe what it does (i.e. 
	 *       "Disable Anonymously Accessible Named Pipes")
	 * \param level The level at which this mitigation policy should be begin to be enforced. This should be Low, 
	 *        Moderate, or High
	 * \param description An optional explanation for the policy (i.e. "Anonymously accessible named pipes can be used 
	 *        in X, Y and Z attacks and should be disabled. See abc.com/xyz for more info [v-123]")
	 */
	MitigationPolicy(const std::wstring& name, EnforcementLevel level, 
					 const std::optional<std::wstring>& description = std::nullopt);

	/**
	 * \brief Enforces the mitgiation policy, applying the change to the system.
	 * 
	 * \return True if the system has the mitigation policy enforced; false otherwise.
	 */
	virtual bool Enforce() const = 0;

	/**
	 * \brief Checks if the changes specified by the mitigation policy match the current state of the
	 *        system.
	 * 
	 * \return True if the system has the changes specified by the mitigation policy enforced; false 
	 *         otherwise.
	 */
	virtual bool MatchesSystem() const = 0;

	/**
	 * \brief Retrieves the name of the mitigation policy
	 * 
	 * \return The name of the policy
	 */
	std::wstring GetPolicyName() const;

	/**
	 * \brief Returns whether or not the mitigation policy is set to be enforced
	 * 
	 * \return True if the mitigation policy is set to be enforced, false otherwise.
	 */
	bool IsEnforced() const;

	/**
	 * \brief Override default enforcement level settings and specify manually whether this policy should be enforced.
	 * 
	 * \param enforced A boolean indicating whether this policy should be enforced.
	 */
	void SetEnforced(bool enforced);

	/**
	 * \brief Set whether or not this policy should be enforced by specifying an enforcement level. If the given level
	 *        is higher than or equal to the policy's enforcement level, the policy will be enforced.
	 *
	 * \param level The level at which the associated mitigation is being enforced.
	 */
	void SetEnforced(EnforcementLevel level);

	/**
	 * \brief Get the minimum level at which the MitigationPolicy will be enforced by default.
	 * 
	 * \return The minimum level at which the MitigationPolicy will be enforced by default.
	 */
	EnforcementLevel GetEnforcementLevel() const;
};